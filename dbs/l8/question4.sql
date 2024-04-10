SELECT DISTINCT Professor.last, Department.name
FROM Professor, Department, ProfessorBelongsToDepartment
WHERE Professor.professorID = ProfessorBelongsToDepartment.professorID
AND Department.deptID = ProfessorBelongsToDepartment.deptID