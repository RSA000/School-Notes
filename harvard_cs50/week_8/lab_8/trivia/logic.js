
// This Changes the correct checkbox to green when clicked and displays a correct message
var correct = document.querySelector(".correct");
correct.addEventListener("click", function()
    {
        var correct = document.querySelector(".correct");
        var feedback = document.querySelector("#feedback1");
        correct.style.backgroundColor = '#6AAB8E';
        feedback.innerHTML = "Correct!";
    });


// This handles incorrect answers by changing the color of the box red and displaying incorrect
var incorrect = document.querySelectorAll(".incorrect");
for (let i = 0; i < incorrect.length; i++)
    incorrect[i].addEventListener("click", function()
    {
        incorrect[i].style.backgroundColor = '#DD8888';
        feedback1.innerHTML = "Incorrect";
    });

// This handles the inputted answer and will display correct if right and incorrect if wrong
var submit_answer = document.querySelector(".submit");
submit_answer.addEventListener("click", function()
    {
        var answer = document.querySelector("#answer1");
        var feedback = document.querySelector("#feedback2");
        if (answer.value.toLowerCase().localeCompare("obsidian") === 0)
        {
            feedback.innerHTML = "Correct!";
            answer.style.backgroundColor = '#6AAB8E';
            submit_answer.style.backgroundColor = '#6AAB8E';
        }
        else
        {
            feedback.innerHTML = "Incorrect";
            answer.style.backgroundColor = '#DD8888';
            submit_answer.style.backgroundColor = '#DD8888';
        }
    });