import Process


class Monitor:
    def __init__(self, pm):
        print("monitor initializing")
        self.Blocked_Process = []
        self.Process_Manager = pm 
        print("monitor ready")

    def wait(self,process_id):
        p = self.Process_Manager.GetProcess(process_id)
        if p is None:
            return
        self.Blocked_Process.append(process_id)
        p.go = False
        while not p.go:
            pass
        
    
    def signal(self,process_id):
        if not len(self.Blocked_Process) == 0 :
            p = self.Process_Manager.GetProcess(self.Blocked_Process.pop(0))
            if p is None:
                return
            p.go = True
            p.caller = process_id 
            caller = self.Process_Manager.GetProcess(process_id)
            if caller is None:
                return
            if not caller.caller is None:
                if self.Process_Manager.GetProcess(caller.caller) is None:
                    return
                self.Process_Manager.GetProcess(caller.caller).go = True
                caller.caller = None
            while not caller.go:
                pass

