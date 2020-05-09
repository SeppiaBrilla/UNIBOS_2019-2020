class Process:
    def __init__(self, id):
        self.id = id
        self.go = True
        self.caller = None

    def __str__(self):
        return "Processo con id:" + str(self.id)


class process_manager:
    def __init__(self):
        self.Process_List = []

    def add_Process(self,process):
        self.Process_List.append(process)

    def GetProcess(self,process_id):
        for p in self.Process_List:
            if p.id == process_id:
                return p
        
        return None
