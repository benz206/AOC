rotations = ["L68", "L30", "R48", "L5", "R60", "L55", "L1", "L99", "R14", "L82"]

position = 50
count = 0

for rotation in rotations:
    direction = rotation[0]
    distance = int(rotation[1:])
    
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
    
    print(f"After {rotation}: position={position}, count={count}")

print(f"\nTotal count: {count}")

