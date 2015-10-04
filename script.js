function printNames(){
	var e = document.getElementById("tendina");
	var strUser = e.options[e.selectedIndex].value;
	document.getElementById('nameList').innerHTML = strUser;
}