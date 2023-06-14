import time
import os

if __name__ == "__main__":

    file = open("instance.txt","r")
    input = file.read()


    # # compilate
    os.system("gcc sek.c -o sek")
    os.system("gcc omp.c -o omp -fopenmp")

    # time_sek = []
    # for _ in range(100):
    #     time_start = time.time()
    #     os.system("./sek "+input)
    #     time_end = time.time()
    #     time_sek.append(time_end - time_start)
    # time_sek = sum(time_sek)/len(time_sek)
    # print(f"sequential time = {round(time_sek*1000,2)} ms")

    # THREADS = input.split(" ")[0]
    # time_omp = []
    # for _ in range(100):
    #     time_start = time.time()
    #     os.system("env OMP_NUM_THREADS="+str(THREADS)+" ./omp "+input)
    #     time_end = time.time()
    #     time_omp.append(time_end - time_start)
    # time_omp = sum(time_omp)/len(time_omp)
    # print(f"openMP {THREADS}   time = {round(time_omp*1000,2)} ms")

    time_start = time.time()
    os.system("./sek "+input)
    time_end = time.time()
    time_sek = time_end - time_start

    THREADS = input.split(" ")[0]
    time_start = time.time()
    os.system("env OMP_NUM_THREADS="+str(THREADS)+" ./omp "+input)
    time_end = time.time()
    time_omp = time_end - time_start

    print(f"sequential time = {round(time_sek*1000,2)} ms")
    print(f"openMP {THREADS} time = {round(time_omp*1000,2)} ms")