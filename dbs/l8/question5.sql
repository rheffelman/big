SELECT Professor.first, Professor.last
FROM Professor, Section
WHERE Section.professorID = Professor.professorID
AND Section.courseID = 2

INTERSECT

SELECT Professor.first, Professor.last
FROM Professor, Section
WHERE Section.professorID = Professor.professorID
AND Section.courseID = 3