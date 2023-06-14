import random

def generate(n,k,min_val=1,max_val=10):

    partitions_size = []
    n_left = n
    for _ in range(k):
        size = random.randint(1, n_left - (k - 1 - _ ) )
        n_left -= size
        partitions_size.append(size)
    partitions_size[0] += n_left


    partitions = [[]]
    for _ in range(partitions_size[0]):
        partitions[0].append( random.randint(min_val,max_val) )
    target_sum = sum(partitions[0])

    for idx in range(1,k):

        partitions.append([])

        target_sum_left = target_sum
        for _ in range(partitions_size[idx]):
            num = random.randint(1,target_sum_left - (partitions_size[idx] - 1 - _) )
            target_sum_left -= num
            partitions[idx].append(num)
        partitions[idx][0] += target_sum_left

    return partitions

if __name__ == "__main__":

    n = 1000000
    k = 1000

    partitions = generate(n,k)
    input = str(k)
    for partition in partitions:
        for el in partition:
            input += " " + str(el)

    file = open("instance.txt","w")
    file.write(input)
    file.close()