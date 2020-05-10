import Monitor
import Process 



class oggetto:
    def __init__(self, obj, n):
        self.obj = obj 
        self.n = n


class mbuf:
    def __init__(self):

        self.process_manager = Process.process_manager() #qualche riga di codice per la gestione dei processi per il monitor
        self.addproc = Process.Process(0)
        self.getproc = Process.Process(1)
        self.process_manager.add_Process(self.addproc)
        self.process_manager.add_Process(self.getproc) #fine gestione processi, ora le cose interessanti

        self.monitor = Monitor.Monitor(self.process_manager) #inizializzo il monitor
 
        self.buffer = [] #ed il buffer 


    def add(self, obj):

        self.monitor.wait(self.addproc.id) #attendo per la mutua esclusione 

        self.buffer.append(obj) #aggiungo il mio oggetto, ho creato la classe oggetto con la molteplicità e l'oggetto così da non gestire separatamente 

        self.monitor.signal(self.addproc.id) #rilascio la mutua esclusione

    def get(self):

        self.monitor.wait(self.getproc.id) #attendo per la mutua esclusione 

        obj = self.buffer[0] #prendo il primo oggetto dalla pila 
        obj.n -= 1 #ne dimunuisco la moltiplicità

        if obj.n <= 0: #controllo se ora la molteplicità è 0
            self.buffer.pop(0) #elimino il valore dal buffer  
        
        self.monitor.signal(self.getproc.id) #rilascio la mutua esclusione 

        return obj.obj
