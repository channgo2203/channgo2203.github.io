InitializeMemory();

foreach input_event do
  ComputeOutput();
  UpdateMemory();
end

InitializeMemory();

foreach period do 
  ReadInputs();
  ComputeOutput();
  UpdateMemory();
end


