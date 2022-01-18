import json
import numpy as np
import matplotlib.pyplot as plt

with open('tennis.json') as f:
    data = json.loads(f.read())
players = set()
seq_count = {}
cnt = 0
max_ballP = -1
min_ballP = 10000
winning_count = 0
for rally in data['dataset']:
    # if len(rally['patterns']) < 5:
    #     continue
    if rally['server'] != 'Djokovic':
        continue
    if rally['winner'] == 'Djokovic':
        winning_count += 1
    players.add(rally['winner'])
    players.add(rally['loser'])
    key = rally['winner'] +'$' + rally['loser'] if rally['winner'] < rally['loser'] else rally['loser'] + '$' + rally['winner']
    if key not in seq_count.keys():
        seq_count[key] = 0
    seq_count[key] += 1
print(winning_count)
print(players)
print([key.split('$') + [seq_count[key]] for key in seq_count])

# print(sum([len([0 for strike in rally['patterns']]) for rally in data['dataset']]))

# print(sum([sum([1 for strike in rally['patterns'] if strike['BallPosition'] > (max_ballP + min_ballP) / 2]) for rally in data['dataset']]))
# print(sum([sum([1 for strike in rally['patterns'] if strike['BallPosition'] <= (max_ballP + min_ballP) / 2]) for rally in data['dataset']]))
# input_x = [strike['BallPosition'] for rally in data['dataset'] for strike in rally['patterns']]
# input_x.sort()
# x = np.array(input_x)
# y = 3 * np.random.rand(len([1 for rally in data['dataset'] for strike in rally['patterns']]))
# print(x.size, y.size)

# colors = np.random.rand(len([1 for rally in data['dataset'] for strike in rally['patterns']]))
# area = (1 * np.array([1 for rally in data['dataset'] for strike in rally['patterns']]))**2  # 0 to 15 point radii

# # x = np.array([1, 2, 3])
# # y = np.array([1, 1, 1])

# plt.scatter(x, y, s=area, alpha=0.5)
# plt.show()