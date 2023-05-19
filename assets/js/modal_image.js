// Get the modal
const modal = document.getElementById("modal");
var modalImg = document.getElementById("modal-image");

// Get the image and insert it inside the modal - use its "alt" text as a caption
const imgs = document.getElementsByClassName("mi")
let is_open = false;
for (let i = 0; i < imgs.length; i++) {
    const img = imgs.item(i);
    img.onclick = function()
    {
        modal.style.display = "block";
        modalImg.src = this.src;
        setTimeout(()=>is_open = true,200)
    }

    window.addEventListener("click", function(event)
    {
        if(is_open)
        {
            modal.style.display = "none";
            is_open = false;
        }
    });
}