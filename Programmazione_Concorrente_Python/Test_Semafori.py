import Semaphores
import Process
import threading


def main():
    p1 = Process.Process(1)
    p2 = Process.Process(2)
    p3 = Process.Process(3)
    pm = Process.process_manager()
    pm.add_Process(p1)
    pm.add_Process(p2)
    pm.add_Process(p3)
    Semaphore = Semaphores.Semaphore(pm)

    t1 = threading.Thread(target= process1, args = (p1,Semaphore))
    t2 = threading.Thread(target= process2, args = (p2,Semaphore))
    t3 = threading.Thread(target= process3, args = (p3,Semaphore))

    t1.start()
    t2.start()
    t3.start()

def process1(process, Semaphore):
    print("processo 1 start")
    while True:
        Semaphore.P(process.id)
        print(process)
        Semaphore.V()
    
def process2(process, Semaphore):
    print("processo 2 start")
    while True:
        Semaphore.P(process.id)
        print(process)
        Semaphore.V()
    
def process3(process, Semaphore):
    print("processo 3 start")
    while True:
        Semaphore.P(process.id)
        print(process)
        Semaphore.V()
    
main()
