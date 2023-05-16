# Analysis of algorithms
Algorithm analysis provides theoretical estimation for required resources (time/memory) to run an algorithm to solve a specific computational problem.

It is the determination of the amount of time and memory resources required for its execution. It is used to predict the behaviour of an algorithm without implementing it on a specific machine. This is only an estimaton and is not perfect.

It is impossible to predict the exact behaviour of an algo due to implementation and host machine differences (and a shit ton of other influencing factors).

### Time and space complexity notations:

- __Big O notation__: Provides upped on running time and psace usage of an algorithm. It is worst case complexity.

- __Big θ notation__: Provides upper and lower bound on rate of growth of algoirhtm, runing time or space complexity. It is average case complexity.

- __Big Ω notation__: Provides lower bound on rate of growth of algorithm, running time or space complexity. It is best case complexity.


## Exmaple - Algorithm to sum the elements of an array
```
def sum (array):                    # counter += 0
  sum = 0                           # counter += 1
  for i in array:                   # counter += (n + 1)
    sum += i                        # counter += n
  return sum                        # counter += 1

# Hence, frequency count = 2n + 3
# Hence, complexity = O(n)
```

### Frequency count (how many times a line of code is to be executed)
- __Function declaration__: counter += 0
- __Function call__: counter += 1
- __Variable declaration (and initialisation)__: counter += 1 (no matter the number of variables, all are initialised/declared all together)
- __For loop__: Condition check runs n + 1 times. Body of loop runs n times.
 