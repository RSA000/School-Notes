

var submit = document.querySelector("#submit_button");

submit.addEventListener("click", function()
    {
        var text = document.querySelector("#feedback1");
        var confirmation = document.querySelector("#submit_verify");
        confirmation.innerHTML = "Submitted!";
    });