with open('day1.txt', 'r') as f:
    position = 50
    count = 0
    
    for line in f:
        line = line.strip()
        if not line:
            continue
        
        direction = line[0]
        distance = int(line[1:])
        
        if direction == 'L':
            start = position
            end = (position - distance + 100) % 100
            
            for i in range(1, distance + 1):
                current = (start - i + 100) % 100
                if current == 0:
                    count += 1
            
            position = end
        else:
            start = position
            end = (position + distance) % 100
            
            for i in range(1, distance + 1):
                current = (start + i) % 100
                if current == 0:
                    count += 1
            
            position = end
    
    print(count)

