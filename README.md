Chef.
Download the folder as zip file then extract anywhere you want then open Spaced Reps.exe


Shown below is the design documentation of the app.
![Spaced Reps](https://github.com/linuxlaber/Spaced-Reps/assets/170599771/d73e85ae-2868-47cf-abe5-325ed9990ecf)

I would like to talk about my struggles in developing the code for option 4 which is Add/Check solution. I have 3 ideas I proposed, 2 didn't work, and only 1 made it out. That 1 idea however is the reason why this project has the feature to add and check solutions. This project was born right after I learned about an algorithm where you have to output the lowest value and I realized that I can structure the date into this format 01-03-1944-Time(timeformat hehe). Notice the pattern, of day-month-year-time. What I did was that the algorithm will read only the lowest 1st and second digit along with fourth and fifth digit where fourth and fifth digit > 1st and second digit in terms of priority (only reading 01 and 03 on the example). Meaning, the day might have a low value, but if the month has a lower value, that task is more likely to be chosen.

Note that the increment for the interval will always be +3 days. You can't customize it. It will follow:
First Revision - day/month/year/time
Second Revision - day+1/month/year/time
Third Revision - day+1+3/month/year/time
Fourth Revision - day+1+3+3/month/year/time
...
...

Idea 1:

Idea 2:

Idea 3:


