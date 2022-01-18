//
// Created by A on 2020/12/22.
//

#include <iostream>
#include "FileLoader.hpp"
#include "BaseAttr.hpp"
#include "json.hpp"
#include <exception>
#define FLITER_SERVER
using namespace std;
using json = nlohmann::json;

list<BaseSeq> extract_tt_sequences(json j) {
    string our_player = "00", opponent = "10";
    try {
        list<BaseSeq> sequenceList = list<BaseSeq>();

        for (auto game: j["data"]["record"]["list"]) {
            for (auto rally: game["list"]) {
                auto events = vector<BaseEvt>();
#ifdef FLITER_SERVER
                if (rally["list"].size() < 3) {
                    continue;
                }
                if (rally["list"][0]["HitPlayer"] == "10") {
                    continue;
                }
#endif
                for (auto strike: rally["list"]) {
                    auto attrs = vector<int>();

                    if (strike["HitPlayer"] == our_player) {
                        attrs.push_back(BaseAttr::from_key_value("ttBallPosition", strike["BallPosition"]["value"]));
                        attrs.push_back(BaseAttr::from_key_value("ttStrikePosition", strike["StrikePosition"]["value"]));
                        attrs.push_back(BaseAttr::from_key_value("ttStrikeTech", strike["StrikeTech"]["value"]));
//                    attrs.push_back(BaseAttr::from_key_value("ttSpinKind", strike["SpinKind"]));
                    } else {

                        attrs.push_back(BaseAttr::from_key_value("ttBallPosition", to_string(strike["BallPosition"]["value"]) + "Op"));
                        attrs.push_back(BaseAttr::from_key_value("ttStrikePosition", to_string(strike["StrikePosition"]["value"]) + "Op"));
                        attrs.push_back(BaseAttr::from_key_value("ttStrikeTech", to_string(strike["StrikeTech"]["value"]) + "Op"));
                    }

                    events.emplace_back(attrs);
                }
                sequenceList.emplace_back(events, rally["winSide"]);
            }
        }

        return sequenceList;
    } catch (exception &msg) {
        throw invalid_argument("Unrecognizable file format!");
    }
}

string ball_position_int(double x) {
    if (x < 0.55) {
        return "Very Low";
    } else if (x < 1.25) {
        return "Low";
    } else if (x < 2) {
        return "Medium";
    }
//    else if (x < 2.9) {
//        return "High";
//    }
    else {
        return "High";
    }
}

list<BaseSeq> extract_badminton_sequences(json j) {
    string our_player = "Momota Kento", opponent = "Opponent";
    try {
        list<BaseSeq> sequenceList = list<BaseSeq>();
        int debug_cnt = 0;
        for (auto rally: j["dataset"]) {
            auto events = vector<BaseEvt>();
#ifdef FLITER_SERVER
            if (rally["patterns"].size() < 7) {
                continue;
            }
            if (rally["server"] != "Momota Kento") {
                continue;
            }
            if (++debug_cnt > 338) {
                break;
            }
#endif
            for (auto strike: rally["patterns"]) {
                auto attrs = vector<int>();
                if (strike["HitPlayer"] == our_player) {
                    attrs.push_back(BaseAttr::from_key_value("btBallPosition", ball_position_int(strike["BallPosition"])));
                    attrs.push_back(BaseAttr::from_key_value("btStrikePosition", strike["StrikePosition"]));
                    attrs.push_back(BaseAttr::from_key_value("btStrikeTech", strike["StrikeTech"]));
                } else {
                    attrs.push_back(BaseAttr::from_key_value("btBallPosition", ball_position_int(strike["BallPosition"]) + "Op"));
                    attrs.push_back(BaseAttr::from_key_value("btStrikePosition", to_string(strike["StrikePosition"]) + "Op"));
                    attrs.push_back(BaseAttr::from_key_value("btStrikeTech", to_string(strike["StrikeTech"]) + "Op"));
                }
//                attrs.push_back(BaseAttr::from_key_value("btHitPlayer", strike["HitPlayer"] == our_player ? our_player : opponent));
//                    attrs.push_back(BaseAttr::from_key_value("ttSpinKind", strike["SpinKind"]));

                events.emplace_back(attrs);
            }
            sequenceList.emplace_back(events, int(rally["winner"] == "Momota Kento"));
        }

        return sequenceList;
    } catch (exception &msg) {
        throw invalid_argument("Unrecognizable file format!");
    }
}

list<BaseSeq> extract_tennis_sequences(json j) {
    string our_player = "Djokovic", opponent = "Opponent";
    try {
        list<BaseSeq> sequenceList = list<BaseSeq>();

        for (auto rally: j["dataset"]) {
            auto events = vector<BaseEvt>();
#ifdef FLITER_SERVER
//            if (rally["patterns"].size() < 7) {
//                continue;
//            }
            if (rally["server"] != our_player) {
                continue;
            }
#endif
            for (auto strike: rally["patterns"]) {
                auto attrs = vector<int>();
                if (strike["HitPlayer"] == our_player) {
                    attrs.push_back(BaseAttr::from_key_value("btBallPosition", strike["BallPosition"]));
                    attrs.push_back(BaseAttr::from_key_value("btStrikePosition", strike["StrikePosition"]));
                    attrs.push_back(BaseAttr::from_key_value("btStrikeTech", strike["StrikeTech"]));
//                    attrs.push_back(BaseAttr::from_key_value("btSpinKind", strike["SpinKind"]));
//                    attrs.push_back(BaseAttr::from_key_value("btGameAction", strike["GameAction"]));
                } else {
                    attrs.push_back(BaseAttr::from_key_value("btBallPosition", to_string(strike["BallPosition"]) + "Op"));
                    attrs.push_back(BaseAttr::from_key_value("btStrikePosition", to_string(strike["StrikePosition"]) + "Op"));
                    attrs.push_back(BaseAttr::from_key_value("btStrikeTech", to_string(strike["StrikeTech"]) + "Op"));
//                    attrs.push_back(BaseAttr::from_key_value("btSpinKind", to_string(strike["SpinKind"]) + "Op"));
//                    attrs.push_back(BaseAttr::from_key_value("btGameAction", to_string(strike["GameAction"]) + "Op"));

                }
//                attrs.push_back(BaseAttr::from_key_value("btHitPlayer", strike["HitPlayer"] == our_player ? our_player : opponent));
//                    attrs.push_back(BaseAttr::from_key_value("ttSpinKind", strike["SpinKind"]));

                events.emplace_back(attrs);
            }
            sequenceList.emplace_back(events, int(rally["winner"] == our_player));
        }

        return sequenceList;
    } catch (exception &msg) {
        throw invalid_argument("Unrecognizable file format!");
    }
}

list<BaseSeq> FileLoader::loadFile(const string& fileName, FileType fileType) {
    try {
        ifstream file(fileName, ios::in);
        if (!file.is_open())
            throw invalid_argument("Cannot open this file!");


        json j;
        file >> j;

        switch (fileType) {
            case FileType::TableTennis:
                return extract_tt_sequences(j);
            case FileType::Badminton:
                return extract_badminton_sequences(j);
            case FileType::Tennis:
                return extract_tennis_sequences(j);
            default:
                throw invalid_argument("The file type is not supported!");
        }
    } catch (exception &msg) {
        cout << "Error: " << msg.what() << endl;
        return list<BaseSeq>();
    }
}
