
echo "Bienvenue dans le Shell ENSEA."
echo "Pour quitter, tapez 'exit'."

while true; do
    read -p "enseash % " input

    # check if user wants to exit
    if [ "$input" == "exit" ]; then

        break
     else
        #Display a message to quit
        echo "Pour quitter, tapez 'exit'."

    fi
done