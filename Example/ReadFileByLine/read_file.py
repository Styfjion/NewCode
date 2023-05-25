if __name__ == '__main__':
    with open('test.env', 'r', encoding='utf-8') as f:
        lines = f.readlines()
        ret = []
        for line in lines:
            ret.append(line.split('=')[0])
        print(','.join(ret))
