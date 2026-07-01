# Copyright (c) 2026 Kacper Lisiak
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>

import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp
from scipy.signal import argrelextrema

#Obowiązujące jednostki: kilometr, sekunda, masa Słońca
#Warunki początkowe:
#Masy:
m1 = 1.441 # [M_Słońca]
m2 = 1.387 # [M_Słońca]
m = m1 + m2 # [M_Słońca]
m_efektywna = m1*m2/m # [M_Słońca]
eta = m_efektywna/m # [1]
#Inne:
G = 132712878914.24 # [km^3 s^-2 M_Słońca^-1]
#Położenia:
initial_position_1 = [0.0, 0.0, 0.0] # [km]
initial_position_2 = [746600.0, 0.0, 0.0] # [km]
#Prędkości:
initial_velocity_1 = [0.0, 0.0, 0.0] # [km s^-1]
initial_velocity_2 = [0.0, 450.0, 0.0] # [km s^-1]
#Razem:
initial_conditions = np.array([
    initial_position_2,
    initial_velocity_2
]).ravel()

#Równanie:
def uklad_rownan(t,S, m, eta, G):
    x = S[0:3]
    dx_dt = S[3:6]
    y = dx_dt

    dy_dt = - G*m*x/np.linalg.norm(x)**3 - (8/5)*eta*m**2/np.linalg.norm(x)**3 * (-(18*np.linalg.norm(y)**2 + 2*m/(3*np.linalg.norm(x)) - 25*(np.dot(x, y)/np.linalg.norm(x))**2)*(np.dot(x, y)/np.linalg.norm(x)**2)*x + (6*np.linalg.norm(y)**2 - 2*m/np.linalg.norm(x) - 15*(np.dot(x, y)/np.linalg.norm(x))**2)*y)
    return np.array([y, dy_dt]).ravel()

#Punkty czasowe:
time_s, time_e = 0, 94200
t_points = np.linspace(time_s, time_e, 942001)

#Rozwiązanie:
solution = solve_ivp(fun=uklad_rownan, t_span=(time_s, time_e), y0=initial_conditions, method="RK45", t_eval=t_points, args=(m, eta, G))

#Teraz trzeba ten wynik jakoś przetworzyć:
polozenie = np.asarray(np.sqrt((solution.y[3]-solution.y[0])**2 + (solution.y[4]-solution.y[1])**2 + (solution.y[5]-solution.y[2])**2))
#wartosc_apoapsis = [746600]
#wartosc_periapsis = []
#czas_apoapsis = [0]
#czas_periapsis = []
#pol_os_wielka = []
#czas_osi = []
#os = [0]

#Szukanie ekstremów położenia:
czas_apoapsis = np.asarray(argrelextrema(polozenie, np.greater))
czas_periapsis = np.array(argrelextrema(polozenie, np.less))

#Tu następuje obliczenie półosi wielkiej:
pol_os_wielka = np.asarray((polozenie[czas_apoapsis] + polozenie[czas_periapsis])/2)
#czas, w którym zachodzi półoś przyjmiemy jako czas, w którym zachodzi apoapsis

#Tu będzie obliczenie tempa zmiany półosi wielkiej w czasie:
tempo_zmiany = []
yyy = 0
for i in range(1, 41):
    yyy = (pol_os_wielka[0][i] - pol_os_wielka[0][i-1])/(czas_apoapsis[0][i] - czas_apoapsis[0][i-1])
    tempo_zmiany.append(yyy)
print(tempo_zmiany)
np.savetxt("tempo_zmiany_półosi_wielkiej.txt", tempo_zmiany, header='Tempo zmiany półosi wielkiej [km/s]')

#Tu są wykresy:
skala = 0.1
plt.plot(t_points, polozenie)
#plt.plot(czas_apoapsis*skala, polozenie[czas_apoapsis], 'x')
#plt.plot(czas_periapsis*skala, polozenie[czas_periapsis], 'x')
plt.plot(czas_apoapsis*skala, pol_os_wielka, 'o')
plt.show()