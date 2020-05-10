import Monitor
import Process

class internalMonitor:
    def __init__(self, timeout, process, pm):
        self.monitor = Monitor.Monitor(pm)
        self.process = process
        self.timeout = timeout
        self.is_time_ended = False

class semtimeout:

    def __init__(self, pm):
        self.process_manager = pm
        self.time = 0
        self.queue = []


    def V(self):
        if len(queue) > 0: #se la coda non è vuota 
            p = queue.pop(0) #estraggo il processo in testa 
            p.monitor.signal(None) #mando una signal al processo bloccato

    def P(self, timeout, process):
        p = internalMonitor(timeout + self.time, process, self.process_manager) #definisco la nuova struttura con un suo monitor interno e un timeout 
        queue.append(p) #inserisco la struttura nella queue in attesa sul monitor
        p.monitor.wait(process.id) #metto in wait il processo
        return p.is_time_ended #il valore ritornato viene settato a true se il processo finisce per timeout
            

    def tick(self):
        time += time #incremento il time 
        for p in self.queue: #scorro i processi bloccati 
            if p.timeout <= time: #se il processo in esame ha il timeout scaduto             
                queue.remove(p) #rimuovo il processo dalla coda dei bloccati 
                p.is_time_ended = True #setto il valore di ritorno a true 
                p.monitor.signal(None) #faccio una signal al monitor del processo