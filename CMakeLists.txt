cmake_minimum_required(VERSION 3.15)
project(MDL_MODULE)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        MDL_MODULE
        test.cpp

        base/BaseAttr.cpp base/BaseAttr.hpp
        base/BaseSeq.cpp base/BaseSeq.hpp
        base/BaseEvt.cpp base/BaseEvt.hpp
        base/json.hpp
        base/FileLoader.cpp base/FileLoader.hpp

        MDL_MODULE/CodeTable.cpp MDL_MODULE/CodeTable.h
        MDL_MODULE/Cover.cpp MDL_MODULE/Cover.h
        MDL_MODULE/Defines.h
        MDL_MODULE/mdl_enter.cpp MDL_MODULE/mdl_enter.h
        MDL_MODULE/Attribute.h
        MDL_MODULE/GetOpt.cpp MDL_MODULE/GetOpt.h
        MDL_MODULE/MathUtil.cpp MDL_MODULE/MathUtil.h
        MDL_MODULE/Event.cpp MDL_MODULE/Event.h
        MDL_MODULE/Node.cpp MDL_MODULE/Node.h
        MDL_MODULE/Params.h
        MDL_MODULE/Pattern.cpp MDL_MODULE/Pattern.h
        MDL_MODULE/Sequence.cpp MDL_MODULE/Sequence.h
        MDL_MODULE/Common.h
        MDL_MODULE/PatternTable.cpp
        MDL_MODULE/Window.cpp MDL_MODULE/Window.h base/BaseDS.cpp base/BaseDS.hpp)