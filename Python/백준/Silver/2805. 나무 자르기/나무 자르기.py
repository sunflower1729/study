import sys
n, h = map(int,sys.stdin.readline().rstrip().split())
tree = list(map(int,sys.stdin.readline().rstrip().split()))
tree.sort(reverse=True)
s=0
l=tree[0]
c=tree[0]//2

while True:
    a = 0
    c=(s+l)//2
    a=sum([i-c if c < i else 0 for i in tree])
    if a > h:
        s = c
    elif a == h:
        print(c)
        break
    else:
        l = c
    if c+1==l and a > h:
        print(c)
        break
