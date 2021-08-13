/* Webpage HTML - this is the homepage*/ 

#ifndef homepage_h
#define homepage_h

const char home_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html5>
<html>
  <head>
    <title>%title% Home</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <meta http-equiv="expires" content="0">
    
    %The_CSS%

   </head>
  <body>
  
    <div id="container">

      <div id="header">
        <h2>%title% - <em>Home</em></h2>
        <div class = "menu-buttons">
          <div class = "buttons ButtonHere">
            <Button1>Home</button1>
          </div>
          <div class = "buttons ButtonClickable">
           <button2 onclick="location.href='/management'">Management</button2>
          </div>
          <div class = "buttons ButtonClickable">
            <Button3 onclick="location.href='/config'">Config</button3>
          </div>
          <div class = "buttons ButtonClickable">
           <button4 onclick="darkFunction()">Dark Mode</button4>
          </div>
        </div>
      </div>  <!-- HEADER -->

      <div id="body"> 
      

      <div class = "name-status" id="state" style="%online%">
       <span class = "name-text">ONLINE</name-text></span>
      </div>

      <div class = "border">
            
        <div class = "name-host">
          <span class = "name-text">IP Address: </name-text></span>
          <span class = "host">%ipplaceholder%</host></span>
        </div>

        <div class = "name-mac">
          <span class = "name-text">MAC Address: </name-text></span>
          <span class = "host">%macplaceholder%</host></span>
        </div>

        <div class = "name-sketch">
          <span class = "name-text">Memory - Sketch Size: </name-text></span>
          <span class = "host">%memsketch%</host></span>
        </div>

        </div> <!-- Border -->

        </br>
        
        <div class = "border">
        
          <span class = "name-text">Device Topics: </name-text></span></br>
          </br>
          <span class = "host">%heart%</host></span></br></br>
          <span class = "host">%flash%</host></span></br></br>
          <span class = "host">%topic1%</host></span></br></br>
          <span class = "host">%topic2%</host></span></br></br>
          <span class = "host">%topic3%</host></span></br></br>
          <span class = "host">%topic4%</host></span></br></br>
       
        
        </div> <!-- Border -->
        
        </br>
        
      </div>  <!-- BODY -->

      <div id="footer">
        <div class="columns mt-10">
          <span class="label label-rounded label-blank"></span> 
          <div class="columns mt-8">
            <div class="columns mt-4">
              <div class="col-12 text-center">
                <span class="label label-rounded mr-2">%IDplaceholder%</span> 
                -
                <span class="label label-rounded label-primary ml-2">%processorplaceholder%</span>
                -
                <span class="label label-rounded mr-2">%type%</span>
              </div>
            </div> 
            <div class="columns mt-8">
              <span class="label label-rounded label-error">%errorplaceholder%</span> 
            </div>
          </div>
        </div>
      </div>  <!-- FOOTER -->
    </div>

    <script>
    %The_SCRIPTS%
    </script>

  </body>
</html>
)rawliteral";

#endif
