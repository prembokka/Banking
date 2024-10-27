document.getElementById("bankForm").addEventListener("submit", function (event) {
    event.preventDefault();

    const name = document.getElementById("name").value;
    const accountNumber = document.getElementById("accountNumber").value;
    const balance = document.getElementById("balance").value;

    const data = {
        name: name,
        accountNumber: accountNumber,
        balance: balance
    };

    fetch("http://localhost:8080/api/register", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(data),
    })
    .then(response => response.json())
    .then(result => {
        alert("Data sent to backend: " + JSON.stringify(result));
    })
    .catch(error => {
        console.error("Error:", error);
    });
});
