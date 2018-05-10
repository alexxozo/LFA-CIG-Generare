# LFA-CIG-Generare
### This algorithm takes a Free Context Grammar and generates all words that have less that a given length.

### Example

**Input:**
```
G:  
N = {S, A} T  = {a, b} 
S → bSbb | A 
A → aA | ε 
```

**Output:**
```
n = 3 
ε, bbb, a, aa , aaa 
n = 4 
ε, bbb, a, aa , aaa, aaaa, babb 
```
