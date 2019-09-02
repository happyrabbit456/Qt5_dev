// factorial.js
.pragma library

function func() {

}

function factorial(a) {
    a = parseInt(a);
    if (a <= 0)
        return 1;
    else
        return a * factorial(a - 1);
}

function jsFunction() {
    var colors = [ "red", "blue", "green", "orange", "purple" ];

    print("hello js printf")

    console.log("Called JavaScript function!")

    var a = 1;
    for (var ii = 1; ii < 10; ++ii)
        a = a * ii;
    console.log("Result: " + a);
}

function countDown() {
    for(var i=0; i<10; i++) {
        console.log('index: ' + i)
    }
}
function countDown2() {
    var i=10;
    while( i>0 ) {
        i--;
    }
}

function getAge(name) {
    // switch over a string
    switch(name) {
    case "father":
        return 58;
    case "mother":
        return 56;
    }
    return unknown;
}

function doIt() {
  var a = [] // empty arrays
  a.push(10) // addend number on arrays
  a.push("Monkey") // append string on arrays
  console.log(a.length) // prints 2
  print(a[0]) // returns 10
  print(a[1]) // returns Monkey
  print(a[2]) // returns undefined
  a[99] = "String" // a valid assignment
  console.log(a.length) // prints 100
  print(a[98]) // contains the value undefined
}
