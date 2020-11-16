#!/usr/bin/env python3
# RTC_UE01_BMI.py
# Gerald Hebinck 09th Nov 2020

from enum import Enum


# enumeration for inputSwitch
class Awaits(Enum):
    WEIGHT = 0
    SIZE = 1
    AGE = 2


# tuple-matrix for BMI
matrixBMI = ((19, 25, 35, 45, 55, 65),
             (19, 20, 21, 22, 23, 24),
             (24, 25, 26, 27, 28, 29))


# function to calculate the BMI
def calcBMI(m, s):
    return round(m/(pow(s, 2)), 2)


# function to rate the BMI based on age
def evaluateBMI(_bmi, age):
    bmi_min = matrixBMI[1][-1]
    bmi_max = matrixBMI[2][-1]
    for i in range(len(matrixBMI[0])-2):
        if(age < matrixBMI[0][i+1]):
            bmi_min = matrixBMI[1][i]
            bmi_max = matrixBMI[2][i]
            break
    if (_bmi < bmi_min):
        return "Untergewichtig"
    elif (_bmi > bmi_max):
        return "Uebergewichtig"
    else:
        return "Normalgewichtig"


# function to aquire a integer input using a switch for the output
def getInput(a):
    switcher = {
        Awaits.WEIGHT: "Geben Sie Ihr Gewicht in kg an \n",
        Awaits.SIZE: 'Geben Sie Ihre Koerpergroesse in m an \n',
        Awaits.AGE: 'Geben Sie Ihr Alter in Jahren an \n'
    }
    invalid = True
    _input = 0
    while (invalid):
        try:
            _input = eval(input(switcher.get(a)))
            invalid = False
        except Exception:
            print("Invalid input!")
    return _input


# Main
def main():
    weight = getInput(Awaits.WEIGHT)
    size = getInput(Awaits.SIZE)
    age = getInput(Awaits.AGE)
    _bmi = calcBMI(weight, size)
    _rated = evaluateBMI(_bmi, age)
    print("BMI: ", _bmi)
    print(_rated)


main()
