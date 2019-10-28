# Extended Rabin-Karp method
#### Task 
Extend the Rabin-Karp method to handle the problem of looking for a given m×m pattern in an n×n array of characters. (The pattern may be shifted vertically and horizontally, but it may not be rotated.)

#### Solution
Calculating the hashes in each column just like the Rabin-Karp in one-dimension, then treat the hashes in each row as the characters and hashing again.
