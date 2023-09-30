class MyClock24:
    def __init__(self,h,m,s):
        # h for hour, m for minute, s for second
        self.__h = (h+24)%24
        self.__m = (m+60)%60
        self.__s = (s+60)%60
    #decorate hours, minutes, seconds as property
    # hours
    @property
    def hours(self):
        return self.__h
    @hours.setter
    def hours(self,new_h):
        self.__h = (new_h+24)%24
    # minutes
    @property
    def minutes(self):
        return self.__m
    @minutes.setter
    def minutes(self,new_m):
        self.__m = (new_m+60)%60
    # property
    @property
    def seconds(self):
        return self.__s
    @seconds.setter
    def seconds(self,new_s):
        self.__s = (new_s+60)%60

    def __str__(self):
        str_h = str(self.__h)
        str_m = str(self.__m)
        str_s = str(self.__s)

        if self.__h < 10:
            str_h = "0" +str_h
        if self.__m < 10:
            str_m = "0" + str_m
        if self.__s < 10:
            str_s  = "0" + str_s
            
        return "{}:{}:{}".format(str_h,str_m,str_s)
    
    def __repr__(self):
        return str({"hours":self.__h, "minutes":self.__m, "seconds":self.__s})

    def tick(self):
        self.__s = (self.__s+61)%60
        if self.__s == 0:
            self.__m = (self.__m +61)%60
            if self.__m == 0:
                self.__h = (self.__h +25)%24
                
    def tick_back(self):
        self.__s = (self.__s+59)%60
        if self.__s == 59:
            self.__m = (self.__m + 59)%60
            if self.__m == 59:
                self.__h = (self.__h+23)%24


    def __calculate_total(self):
        return self.__h*3600 + self.__m*60 + self.__s
    
    def __eq__(self,other):
        if self.__h == other.__h and self.__m == other.__m and self.__s == other.__s:
            return True
        return False
    
    def __ne__(self,other):
        if self.__h != other.__h or self.__m != other.__m or self.__s != other.__s:
            return True
        return False
    
    def __ge__(self,other):
        s_total = self.__calculate_total()
        o_total = other.__calculate_total()
        if s_total >= o_total:
            return True
        return False

    def __gt__(self,other):
        s_total = self.__calculate_total()
        o_total = other.__calculate_total()
        if s_total > o_total:
            return True
        return False
    def __le__(self,other):
        s_total = self.__calculate_total()
        o_total = other.__calculate_total()
        if s_total <= o_total:
            return True
        return False
    
    def __lt__(self,other):
        s_total = self.__calculate_total()
        o_total = other.__calculate_total()
        if s_total < o_total:
            return True
        return False
    

    def __add__(self,other):
        if type(other) == int:
            for i in range(other):
                self.tick()
            return self
        new_s = self.__s + other.__s
        if new_s > 59:
            add_m = new_s // 60
            new_s = new_s % 60
        else:
            add_m = 0
            
        new_m = self.__m + other.__m + add_m
        if new_m > 59:
            add_h = new_m // 60
            new_m = new_m % 60
        else:
            add_h = 0
            
        new_h = (self.__h + other.__h + add_h + 24)%24
        
        return MyClock24(new_h,new_m,new_s)

    def __sub__(self,other):
        if type(other) == int: 
            for i in range(other):
                self.tick_back()
            return self
        new_s = self.__s - other.__s
        if new_s <0 :
            sub_m = new_s // 60
            new_s = (new_s+60) % 60
        else:
            sub_m = 0
            
        new_m = self.__m - other.__m + sub_m
        if new_m < 0:
            sub_h = new_m // 60
            new_m = (new_m + 60) % 60
        else:
            sub_h = 0
            
        new_h = (self.__h - other.__h + sub_h + 24) % 24
        
        return MyClock24(new_h,new_m,new_s)

