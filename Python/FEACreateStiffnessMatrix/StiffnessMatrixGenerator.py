#This will allow the user to create a stiffness matrix for a 2 noded bar element using direct stiffness method,
#for any rotated orientation

#Nicholas deGrasse, 4/15/2020

import numpy
import math


def createMatrix(E, A, L, angle):
    #convert to radians
    angleRads = math.radians(angle)
    c = math.cos(angleRads)
    s = math.sin(angleRads)

    #stiffness
    k = (A*E)/L

    #create matrix
    stiffnessMatrix = k * numpy.array([[c**2, c*s, -c**2, -c*s], [c*s, s**2, -c*s, -s**2], [-c**2, -c*s, c**2, c*s], [-c*s, -s**2, c*s, s**2]])
    print(stiffnessMatrix)

#Example values
E = 30 * 10**6               #Modulus of elasticity for steel (psi)
A = 5                        #Area, in inches squared
L = 120                      #Length of element, in inches
angle = 30                   #Local angle of rotation wrt the global x axis

createMatrix(E, A, L, angle) #This will return a stiffness matrix for a bar