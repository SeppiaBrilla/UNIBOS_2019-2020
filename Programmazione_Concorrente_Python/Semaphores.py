import Process 



class Semaphore:
    def __init__(self,pm):
        self.Value = 1
        self.Blocked_Process = []
        self.Process_Manager = pm 

    def P(self,process_id):
        self.Value -=1
        if self.Value < 0:
            p = self.Process_Manager.GetProcess(process_id)
            if p is None:
                return
            self.Blocked_Process.append(process_id)
            p.go = False
            while not p.go:
                pass

    def V(self):
        self.Value += 1
        if self.Value <= 0:
            p = self.Process_Manager.GetProcess(self.Blocked_Process.pop(0))
            if p is None:
                return
            p.go = True