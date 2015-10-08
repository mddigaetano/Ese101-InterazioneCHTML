function printNames(){
	var e = document.getElementById("tendina");
	var array = JSON.parse(e.options[e.selectedIndex].value);
	array = array.sort();
	var i = 0;
	
	document.getElementById('nameList').innerHTML = "";
	for(i=0;i<array.length;i++){
		document.getElementById('nameList').innerHTML += array[i]+"<br>";
	}
}