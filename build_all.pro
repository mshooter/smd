TEMPLATE = subdirs 
SUBDIRS = deformationLib demo tests

tests.depend = deformationLib 
demo.depend  = deformationLib

