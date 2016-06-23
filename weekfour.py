import sys
if __name__ == "__main__":
    param = sys.argv

node = 0;

f = open(param[1], "r")
data = f.readlines()
f.close()

node = int(data[0])
branch_number = int(data[1+node])

branch = [[0 for i in range(node)] for j in range(node)]
score = [100 for i in range(node)]
sendscore = [[0 for i in range(node)] for j in range(node)]

node1 = -1
node2 = -1

for a in range(2+node, 2+node+branch_number):
    node1 = ord(data[a][0]) - 65
    node2 = ord(data[a][2]) - 65
    branch[node1][node2] = 1

send = [0 for i in range(node)]

for i in range(node):
    for j in range(node):
        if branch[i][j] == 1:
            send[i] += 1

times = 0
loop = int(param[2])

while times < loop:
    for i in range(node):
        for j in range(node):
            sendscore[i][j] = 0
            if branch[i][j] == 1:
                sendscore[i][j] = float(score[i])/send[i]
    for j in range(node):
        score[j] = 0
        for i in range(node):
            score[j] += sendscore[i][j]
    times += 1

sumscore = 0
for i in range(node):
    print "node %s 's score : %f " % (chr(i+65) , score[i])
    sumscore += score[i]

print "sum: %f" % sumscore


