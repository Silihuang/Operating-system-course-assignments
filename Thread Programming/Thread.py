import threading
import queue
import multiprocessing
import time

def GetList(file):
    data = file.read() # 讀取檔案裡的一組資料
    ContentList = data.split()
    # 以空格为分隔符，包含 \n。spilt()第二個參數為多分成幾分
    # ContentList包含所有資料
    int_ContentList = list(map(int, ContentList))
    # 使用map將ContentList裡的資料都轉成Int型別
    return int_ContentList


def GetDividedList(KNum, file):
    int_ContentList = GetList(file)
    CLlength = len(int_ContentList) # 資料的總數
    size = len(int_ContentList) // KNum  # 每份的數目
    SepratedList = []
    if KNum != 1 :
        # 將資料分成k份
        for i in range(0, KNum * size, size):
            SepratedList.extend([int_ContentList[ i : i+size ] ] )

        SepratedList[KNum-1].extend(int_ContentList[ KNum*size : CLlength])
        # 將沒切到剩餘的的element放入List最後一欄中!!!!!!!!!!!!!!
    else :
        SepratedList.append(int_ContentList[ 0 : CLlength ])

    return SepratedList

def ProcessBubbleMerge( Data, q):
    # 特別為Problem4設計
    # Data為K份資料
    for i in Data:
        # 對每份資料bubble sort
        BubbleSort(i, q)
    while q.qsize() >= 2 :
        # 超過兩份以上資料才MergeSort
        leftlist = q.get()
        rightlist = q.get()
        MergeSort(leftlist, rightlist, q)

def BubbleSort( data, queue ) :
    Listlength = len(data)
    # data的長度
    for i in range(Listlength):
        for j in range(Listlength - i - 1 ):
            if data[j] > data[j + 1]:
                data[j], data[j + 1] = data[j + 1], data[j]
    queue.put(data)

def MergeSort( leftlist, rightlist, q ):

    MergeList = []  # merge完的list
    left, right = 0, 0
    leftlist_length = len(leftlist)
    rightlist_length = len(rightlist)

    while left < leftlist_length and right < rightlist_length:  # 若數量不夠merge則跳出迴圈
        if leftlist[left] < rightlist[right] :
            # 左 < 右
            MergeList.append(leftlist[left])
            left = left + 1
        else :
            # 左 > 右
            MergeList.append(rightlist[right])
            right = right + 1

    # 比完後，將剩餘element放入MergeList中
    if left == len(leftlist):
        MergeList.extend(rightlist[right:rightlist_length])
    else:
        # right == rightlist_length
        MergeList.extend(leftlist[left:leftlist_length])

    q.put(MergeList)  # 將merge完的list放到queue裡


def WriteFile(fileName, list, time):  # 寫檔

    fileName = fileName[ 0 : len(fileName) - 4]
    # 將".txt"刪掉，只留下檔名
    file = open(fileName + '_output.txt', "w") # 寫檔
    file.write('排序:\n')
    for i in list:
        file.write(str(i) + ' ')
    file.write('\n執行時間 : {:.5f} seconds'.format(time))
    file.close()


def problem1(filename, file):
    # fileName 檔案名稱
    # file用來操控檔案
    data = GetList(file)
    # 放入queue裡
    q = queue.Queue(len(data))
    start = time.perf_counter() # 計時開始
    BubbleSort( data, q )  # 泡沫排序
    timespent = time.perf_counter() - start  # 花費的時間
    print('Time:' + str(timespent)) # 印執行時間
    WriteFile(fileName, q.get(), timespent)


def problem2(fileName, file):
    threads = []
    merge_threads = []
    KNum = ''
    while not KNum.isdigit():
        # 此迴圈為防呆，要求輸入數字
        KNum = input('請輸入要切成幾份 : ')

    KNum = int(KNum)
    SepratedList = GetDividedList(KNum, file)  # 讀取分完的資料
    q = queue.Queue(KNum)  # 用來放入分等份且泡沫排序完的Queue

    i, j = 0, 0
    for i in range(KNum):
        t = threading.Thread(target=BubbleSort, args=(SepratedList[i], q))
        # 用來指定你要執行哪一個function，target那邊打上你要的function，幫線程取名，加上name，如果要加入參數，args那邊加入
        threads.append(t)
        # 建立KNum個子執行緒(未執行)
    start = time.perf_counter()  # 開始計時

    t, t2 = 0, 0
    while t < KNum or t2 < KNum - 1:  # k個bubblesort、k-1個mergesort
        if t < KNum:  # 開始泡沫排序法
            threads[t].start()    # 開始執行緒
            t = t + 1
        if q.qsize() >= 2:
            # queue裡面大於兩份，也就是分兩份以上(KNum>=2)才MergeSort
            leftlist = q.get()
            rightlist = q.get()
            # mergesort的執行緒
            merge = threading.Thread(target=MergeSort, args=(leftlist, rightlist, q))
            merge.start()
            # 建立MergeSort的子執行緒(未執行)
            merge_threads.append(merge)
            t2 = t2 + 1

    for i in merge_threads:
        # 等待mergesort的Thread
        i.join()

    timespent = time.perf_counter() - start  # 結束計時

    print('Time: ' + str(timespent))
    WriteFile(fileName, q.get(), timespent )


def problem3(fileName, file):
    processes = []
    merge_processes = []
    KNum = ''

    while not KNum.isdigit():
        # 防呆
        KNum = input('請輸入要切成幾份 : ')
    KNum = int(KNum)
    SepratedList = GetDividedList(KNum, file)  # 分等份完的List
    manager = multiprocessing.Manager() # 建立一個Manager物件
    q = manager.Queue(KNum)  # 等待bubblesort的Queue

    for i in range(KNum):
        p = multiprocessing.Process(target=BubbleSort, args=(SepratedList[i], q))
        # 用來指定你要執行哪一個function，target那邊打上你要的function，幫線程取名，加上name，如果要加入參數，args那邊加入
        processes.append(p)
        # 建立KNum個Processes(未執行)

    start = time.perf_counter()  # 開始計時
    mergenum, p = 0, 0
    while p < KNum or mergenum < KNum - 1:  # k個bubblesort、k-1個mergesort
        if p < KNum:  # 開始bubblesort
            processes[p].start()  # 開始processes
            p = p + 1
        if q.qsize() >= 2:
            # queue裡面大於兩份，也就是分兩份以上(KNum>=2)才MergeSort
            leftlist = q.get()
            rightlist = q.get()
            mp = multiprocessing.Process(target=MergeSort, args=(leftlist, rightlist, q))
            mp.start()
            merge_processes.append(mp)
            mergenum = mergenum + 1

    for i in merge_processes:
        # 等待mergesort的process
        i.join()

    timespent = time.perf_counter() - start  # 結束計時

    print('Time: ' + str(timespent))
    WriteFile(fileName, q.get(), timespent)


def problem4(fileName, file):
    KNum = ''
    while not KNum.isdigit():
        # 防呆
        KNum = input('請輸入要切成幾份 : ')
    KNum = int(KNum)
    SepratedList = GetDividedList(KNum, file)  # 分等份完的List
    manager = multiprocessing.Manager() # 建立一個Manager物件
    q = manager.Queue(KNum)   # 等待bubblesort的Queue

    start = time.perf_counter()  # 開始計時
    pbm = multiprocessing.Process(target=ProcessBubbleMerge, args=(SepratedList, q))
    pbm.start()
    pbm.join()

    timespent = time.perf_counter() - start  # 結束計時
    print('Time: ' + str(timespent))
    WriteFile(fileName, q.get(), timespent)

if __name__ == '__main__':

    fileName = input('Please Enter a file name : ')
    # 輸入檔名( fileName為檔名 )
    file = open(fileName, "r")
    # 讀取，"r"指讀取模式
    # file為操控檔案的物件
    ProblemNum = file.read(1)  # read()裡的數字為讀入的字串長度，由txt檔的第一個數判斷第幾個Problem
    if ProblemNum == '1':
        problem1(fileName, file)
    elif ProblemNum == '2':
        problem2(fileName, file)
    elif ProblemNum == '3':
        problem3(fileName, file)
    elif ProblemNum == '4':
        problem4(fileName, file)

    print('Terminated~')  #結束
    input()  # 輸入任意鍵結束