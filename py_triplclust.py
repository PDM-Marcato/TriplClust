

import pyTriplClust
import numpy as np



# Path to your text file
filename = "test2.dat"

# Load the file (assumes space or tab separated values)
vX, vY, vZ = np.loadtxt(filename, unpack=True)


obj = pyTriplClust.Run_clustering()
inicia = obj.Init(vX, vY, vZ, True)
resuelve = obj.Solve()
clusters = obj.GetIDs()

print('number of clusters: ', len(clusters))


print(clusters)

for c in clusters:        
        print(c)
        
    
