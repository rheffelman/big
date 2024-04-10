select student.first, student.last
from Section, StudentTakesSection, professor, student
where StudentTakesSection.ssn = student.ssn
and section.sectionID = StudentTakesSection.sectionID
AND section.professorID = professor.professorID
and professor.professorID = 1
group by student.ssn
having count(*) > 1