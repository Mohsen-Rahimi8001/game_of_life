import random
import os
import time
import datetime

def evolution(world):
    h = len(world)
    w = len(world[0])
    tw = [[i for i in row] for row in world]
    
    for i in range(h):
        for j in range(w):
            naibs = world[i-1][j-1] + world[i-1][j] + world[i-1][(j+1)%w] + world[i][j-1] + world[i][(j+1)%w] + world[(i+1)%h][j-1] + world[(i+1)%h][j] + world[(i+1)%h][(j+1)%w]
            
            if naibs > 3:
                tw[i][j] = 0
            elif naibs < 2:
                tw[i][j] = 0
            elif naibs == 3:
                tw[i][j] = 1

    return tw


def show(world):
    os.system("clear")
    print(datetime.timedelta(seconds=time.time()-START))
    for row in world:
        for col in row:
            print("\033[92m" + "*" if col else "\033[0m" + ".", end=" ")
        print("\033[0m")


def random_creature(world):
    for i in range(len(world)):
        for j in range(len(world[0])):
            if random.randint(1, 30) == 1:
                world[i][j] = 1 if not world[i][j] else 0
    return world


w, h = 30, 30

world = [[0 for _ in range(w)] for _ in range(h)]

START = time.time()

#glider
#world[5][5] = 1
#world[4][4] = 1
#world[6][5] = 1
#world[6][4] = 1
#world[6][3] = 1

# middle size space ship
world[3][1] = 1
world[3][2] = 1
world[3][3] = 1
world[2][4] = 1
world[2][5] = 1
world[3][5] = 1
world[3][6] = 1
world[4][5] = 1
world[4][4] = 1
world[4][3] = 1
world[4][2] = 1
world[4][1] = 1
world[5][2] = 1
world[5][3] = 1
world[5][4] = 1


#blinker
world[2][26] = 1
world[3][26] = 1
world[4][26] = 1

i = 0
while True:
    if not i % 8:
        world = random_creature(world)

    world = evolution(world)
    show(world)
    i += 1
    time.sleep(0.3)

