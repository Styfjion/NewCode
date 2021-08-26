import numpy as np
test = np.array(range(10))
print(test)
filter = [False] * 5 + [True] * 5
print(filter)
rslt = test[filter]
print(rslt)
