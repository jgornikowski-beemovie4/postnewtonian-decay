# Copyright (c) 2026 Jakub Górnikowski
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

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def to_latex_sci(value):
    if value == 0:
        return r"$0$"
    exponent = int(np.floor(np.log10(abs(value))))
    coeff = value / (10**exponent)
    
    coeff_str = f"{coeff:.1f}"
    if coeff_str.endswith(".0"):
        coeff_str = coeff_str[:-2]
        
    if coeff_str == "1":
        return rf"$10^{{{exponent}}}$"
    elif coeff_str == "-1":
        return rf"$-10^{{{exponent}}}$"
        
    return rf"${coeff_str} \times 10^{{{exponent}}}$"


plt.rcParams.update({
    "text.usetex": True,
    "font.family": "serif",
    "text.latex.preamble": (
        r"\usepackage[T1]{fontenc}"
        r"\usepackage[utf8]{inputenc}"
        r"\usepackage{polski}"
        r"\usepackage{amsmath}"
    )
})

steps = 576000
dt = 0.1
seconds = dt * steps


x1, x2 = 278918 * dt, 557168 * dt
y1, y2 = 3.15012e+06, 3.14411e+06

df = pd.read_csv('distances.csv', header=None)

distance = df.values.flatten()


time = np.linspace(0.0, seconds, len(distance))

fig, ax = plt.subplots(figsize=(8, 6))

ax.plot(time, distance, color='green', linewidth=1.5)

ax.set_title(
	r"Poprawki postnewtonowskie, $\Delta |\mathbf{x}|$ i $\Delta t$" , fontsize=14
	)

ax.set_xlabel(r"czas [s]", fontsize=12)
ax.set_ylabel(r"względna odległość $\mathbf{x}$ [km]", fontsize=12)

ax.grid(True, alpha=0.6)

ax.axvline(x=x1, color='gray', linestyle=':', linewidth=1.2)
ax.axvline(x=x2, color='gray', linestyle=':', linewidth=1.2)
ax.axhline(y=y1, color='gray', linestyle=':', linewidth=1.2)
ax.axhline(y=y2, color='gray', linestyle=':', linewidth=1.2)

plt.draw()

xlim = ax.get_xlim()
ylim = ax.get_ylim()

visible_xticks = [t for t in ax.get_xticks() if xlim[0] <= t <= xlim[1]]
visible_yticks = [t for t in ax.get_yticks() if ylim[0] <= t <= ylim[1]]

ax.set_xticks(visible_xticks + [x1, x2])
xtick_labels = [to_latex_sci(t) for t in visible_xticks] + [r"$x_1$", r"$x_2$"]
ax.set_xticklabels(xtick_labels)

ax.set_yticks(visible_yticks + [y1, y2])
ytick_labels = [to_latex_sci(t) for t in visible_yticks] + [r"$y_1$", r"$y_2$"]
ax.set_yticklabels(ytick_labels)


filename = "pn-plot.png"
plt.savefig(filename, dpi=300, bbox_inches='tight')

plt.show()