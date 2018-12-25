class Lazy:
    def __init__(self, f, args):
        self.evaluated = False
        self.value = None
        self.f = f
        self.args = args
    def force(self):
        if not self.evaluated:
            self.value = self.f(self.args)
            self.evaluated = True
        return self.value


def identity(x):
    print "Evaluating identity()!"
    return x
    
if __name__ == '__main__':
    lazy_ten = Lazy(identity, 10)
    print "Evaluating lazy ten:"
    result = lazy_ten.force()
    print "Result: " + str(result)
    print
    print "Evaluating lazy ten again:"
    result = lazy_ten.force()
    print "Result: " + str(result)