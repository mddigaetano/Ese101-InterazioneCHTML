function printNames(){
	var Dirigente = '["Romana", "Rita"]';
	var Docente = '["Daniela", "Maria Teresa", "Gianni Mario"]';
	var Studente = '["Nicola", "Francesco", "Luigi", "Amedeo"]';
    var e = document.getElementById("tendina");
    var array = JSON.parse(eval(e.options[e.selectedIndex].text));
    array = array.sort();
    i=0;
   document.getElementById('nameList').innerHTML = "";
   for(i=0;i<array.length;i++){
       document.getElementById('nameList').innerHTML += array[i]+"<br>";
   }
}
