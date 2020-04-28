# This program will create CSV with the total potential energy for a 1D two noded bar.
# Just define initial displacement, forces, and material/size properties, and the code creates a
# csv file with the displacement of the each node, and the total potential energy

# Nicholas deGrasse, 4/23/2020

import numpy
import csv

#This returns minimum total potential energy based on d matrix, k matrix, and f1 and f2
def minEnergy(d, k, f1, f2):

    #transpose d matrix
    dT = d.transpose()

    #pull out displacement values from displacement matrix
    u1 = d[0]
    u2 = d[1]

    #store results from multiplying matrices
    temp = 0.5 * numpy.matmul(dT, k)
    temp = numpy.matmul(temp, d)

    #subtract applied forces (neglects body and surface forces)
    minE = temp - (u1 * f1) - (u2 * f2)

    #return total potential energy
    return minE[0]


# Define material and size properties, as well as initial displacements
A = 2               #Area
E = 30 * 10**6      #Modulus of elasticity
L = 30              #Length of the element
f1 = 0              #force at node 1
f2 = -20000         #force at node 2
u1 = 0              #Initial displacement at node 1
u2 = 0              #Initial displacement at node 2
ktemp = (A*E) / L   #Temporarily store value for K

u1Lim = 0.02        #Max/min value to test for displacement at node 1
u1Step = 0.004      #Interval to increase/decrease displacement at node 1 by

u2Lim = -0.02       #Max/min value to test for displacement at node 2
u2Step = -0.004     #Interval to increase/decrease displacement at node 1 by
u2Initial = u2      #Create temporary placeholder to reset u2 everytime

# Create/ open csv file
with open('output.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['displacement 1', 'displacement 2', 'energy'])

    # While loop tests multiple displacements for u1
    while u1 <= u1Lim:

        #While loop tests displacements for u2
        while u2 >= u2Lim:

            # Define matrices
            d = numpy.array([[u1], [u2]])
            k = numpy.array([[ktemp, -ktemp], [-ktemp, ktemp]])

            # Get total potential energy
            energy = minEnergy(d, k, f1, f2)

            # Write displacement of u2 and energy
            writer.writerow([u1, u2, energy])

            # Increase displacement by a set value
            u2 += u2Step
            #End nested while loop

        #reset value for u2, increase u1
        u2 = u2Initial
        u1 = u1 + u1Step
        #End while loops