
public void serialEvent(Serial myPort) { // sensor input via serial port with exception handling
  try
  {
    while ( myPort.available() > 0) // do only when port is available
    {  
      if (val != null) // check for NullPointerException
      {
        val = myPort.readStringUntil('\n');         // read data and store string in val
        values = int(split(val, ':')); // split datapackage and convert to float
      }
    }
  }
  catch (Exception e) { // exception handling
    println(e);
  }
}
