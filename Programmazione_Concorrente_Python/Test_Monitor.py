import Monitor as monitor
import threading


def main():
    p1 = monitor.Process(1)
    p2 = monitor.Process(2)
    p3 = monitor.Process(3)
    pm = monitor.process_manager()
    pm.add_Process(p1)
    pm.add_Process(p2)
    pm.add_Process(p3)
    Monitor = monitor.Monitor(pm)

    t1 = threading.Thread(target= process1, args = (p1,Monitor))
    t2 = threading.Thread(target= process2, args = (p2,Monitor))
    t3 = threading.Thread(target= process3, args = (p3,Monitor))

        t1.start()
    t2.start()
    t3.start()

def process1(process, monitor):
    print("processo 1 start")
    first = True
    while True:
        if not first:
            monitor.wait(process.id)
        else:
            first = False
        print(process)
        monitor.signal(process.id)
    
def process2(process, monitor):
    print("processo 2 start")
    while True:
        monitor.wait(process.id)
        print(process)
        monitor.signal(process.id)
    
def process3(process, monitor):
    print("processo 3 start")
    while True:
        monitor.wait(process.id)
        print(process)
        monitor.signal(process.id)
    
main()
