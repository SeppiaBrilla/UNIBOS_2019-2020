import Process 

#


class Message:
    def __init__(self, message, sender, reciver):
        self.message = message 
        self.sender = sender 
        self.receiver = reciver

    def __str__(self):
        return 'messaggio inviato da: '+ str(self.sender) + ' per: '+ str(self.receiver) + ' con testo: '+ self.message




class Message_Passing:
    def __init__(self, sinc_rec, sinc_send, n_proc, pm):
        
        self.sinc_Rec = sinc_rec
        self.sinc_Send = sinc_send
        self.process_Manager = pm
        self.mail_Box = []
        for i in range(n_proc):
            lista = []
            self.mail_Box.append(lista)


    def send(self, message):

        self.mail_Box[message.sender].append(message)

        if self.sinc_Send:
            p = self.process_Manager.GetProcess(message.sender)
            p.go = False
            while not p.go:
                pass




    def recive(self, sender, reciver):
        
        message = self.scan(sender, reciver)
        if message is None:

            if not self.sinc_Rec:
                return None

            while message is None:
                p = self.scan(sender, reciver)
        
        if self.sinc_Send:
            self.process_Manager.GetProcess(sender).go = True

        return message
            


    def scan(self, sender, reciver):
        if sender == '*':
            for messages in self.mail_Box:
                for message in messages:
                    if reciver == message.reciver:
                        return message
            
            return None

        for message in self.mail_Box[sender]:
            if reciver == message.receiver:
                return message
        
        return None
