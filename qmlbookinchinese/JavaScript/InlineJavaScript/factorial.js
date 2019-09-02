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
