import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
/**
 * Write a description of class Taller here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Taller
{
    // instance variables
    private JFrame frame;

    /**
     * Constructor for objects of class Taller
     */
    public Taller()
    {
        makeFrame();
    }

    /**
     * An example of a method - replace this comment with your own
     * 
     * @param  y   a sample parameter for a method
     * @return     the sum of x and y 
     */

    private void quit()
    {
        System.exit(0);
    }

    private void showStaff()
    {
        JOptionPane.showMessageDialog(frame, "Plantilla", "No users", 
                JOptionPane.INFORMATION_MESSAGE);
    }

    private void showCustom() 
    {
        JOptionPane.showMessageDialog(frame, "Clientes", "No clientes", 
                JOptionPane.INFORMATION_MESSAGE);
    }
    
    public void makeFrame()
    {
        frame = new JFrame("TUNED");
        makeMenuBar(frame);

        //Container contentPane = frame.getContentPane();
        JPanel contentPane = (JPanel)frame.getContentPane();

        JLabel label = new JLabel("Contenido");
        contentPane.add(label);

        frame.pack();
        frame.setVisible(true);
    }

    private void makeMenuBar(JFrame frame)
    {
        JMenuBar menubar = new JMenuBar();
        frame.setJMenuBar(menubar);

        JMenu startMenu = new JMenu("Inicio");
        menubar.add(startMenu);
        JMenuItem quitItem = new JMenuItem("Salir");
            quitItem.addActionListener(e -> quit());
        startMenu.add(quitItem);

        JMenu userMenu = new JMenu("Usuarios");
        menubar.add(userMenu);
        JMenuItem staffUser = new JMenuItem("Plantilla");
            staffUser.addActionListener(e -> showStaff());
        userMenu.add(staffUser);
        JMenuItem customUser = new JMenuItem("Clientes");
            customUser.addActionListener(e -> showCustom());
        userMenu.add(customUser);


    }
}
