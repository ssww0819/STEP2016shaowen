def readNumber(line, index):
    number = 0
    while index < len(line) and line[index].isdigit():
        number = number * 10 + int(line[index])
        index += 1
    if index < len(line) and line[index] == '.':
        index += 1
        keta = 0.1
        while index < len(line) and line[index].isdigit():
            number += int(line[index]) * keta
            keta *= 0.1
            index += 1
    token = {'type': 'NUMBER', 'number': number}
    return token, index

def readPlus(line, index):
    token = {'type': 'PLUS'}
    return token, index + 1

def readMinus(line, index):
    token = {'type': 'MINUS'}
    return token, index + 1

def readMultiply(line, index):
    token = {'type': 'MULTIPLY'}
    return token, index + 1

def readDivide(line, index):
    token = {'type': 'DIVIDE'}
    return token, index + 1

def tokenize(line):
    tokens = []
    index = 0
    while index < len(line):
        if line[index].isdigit():
            (token, index) = readNumber(line, index)
        elif line[index] == '+':
            (token, index) = readPlus(line, index)
        elif line[index] == '-':
            (token, index) = readMinus(line, index)
        elif line[index] == '*':
            (token, index) = readMultiply(line, index)
        elif line[index] == '/':
            (token, index) = readDivide(line, index)
        else:
            print 'Invalid character found: ' + line[index]
            exit(1)
        tokens.append(token)
    return tokens

def evaluate1(tokens):
    tokens1 = []
    index = 0
    index1 = 0
    tokens1.append(tokens[index])
    index +=1
    index1 += 1
    while index < len(tokens):
        if tokens[index]['type'] == 'NUMBER':
            if tokens[index - 1]['type'] == 'PLUS':
                tokens1.append(tokens[index - 1])
                tokens1.append(tokens[index])
            elif tokens[index - 1]['type'] == 'MINUS':
                tokens1.append(tokens[index - 1])
                tokens1.append(tokens[index])
            elif tokens[index - 1]['type'] == 'MULTIPLY':
                tokens1[index1 - 2]['number'] = tokens1[index1 - 2]['number'] * tokens[index]['number']
                index1 = index1 - 2
            elif tokens[index - 1]['type'] == 'DIVIDE':
                tokens1[index1 - 2]['number'] = float(tokens1[index1-2]['number'])/ tokens[index]['number']
                index1 = index1 - 2
            else:
                print 'Invalid syntax'
        index += 1
        index1 += 1
    return tokens1

def evaluate2(tokens1):
    answer = 0
    tokens1.insert(0, {'type': 'PLUS'}) # Insert a dummy '+' token
    index = 1
    while index < len(tokens1):
        if tokens1[index]['type'] == 'NUMBER':
            if tokens1[index - 1]['type'] == 'PLUS':
                answer += tokens1[index]['number']
                #print answer
            elif tokens1[index - 1]['type'] == 'MINUS':
                answer -= tokens1[index]['number']
            else:
                print 'Invalid syntax'
        index += 1
    return answer


while True:
    print '> ',
    line = raw_input()
    tokens = tokenize(line)
    #print tokens
    tokens1 = evaluate1(tokens)
    #print tokens1
    answer = evaluate2(tokens1)
    print "answer = %f\n" % answer
