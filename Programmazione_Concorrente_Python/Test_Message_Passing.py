import Message_Passing
import Process
import threading


def main():
        p1 = Process.Process(1)
        p2 = Process.Process(2)
        pm = Process.process_manager()
        pm.add_Process(p1)
        pm.add_Process(p2)
        Mailer = Message_Passing.Message_Passing(True, True, 2, pm)

        t1 = threading.Thread(target= process1, args = (p1,Mailer))
        t2 = threading.Thread(target= process2, args = (p2,Mailer))

        t1.start()
        t2.start()

def process1(process, Mailer):
    message = Message_Passing.Message('ciao mondo!', 1, 2)
    Mailer.send(message)
    print('p1 done!')

def process2(process, Mailer):
    print(Mailer.recive(1, 2))
    print('p2 done!')



main()