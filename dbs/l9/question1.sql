select course.name, section.sectionID
from course, section
where section.courseID = course.courseID
and course.credits < 4