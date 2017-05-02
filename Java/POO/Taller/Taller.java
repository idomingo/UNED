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
        frame = new JFrame("TUNED - Talleres y Tunning UNED");
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
        final int SHORTCUT_MASK =
            Toolkit.getDefaultToolkit().getMenuShortcutKeyMask();

        JMenuBar menubar = new JMenuBar();
        frame.setJMenuBar(menubar);

        JMenu menu;
        JMenuItem item;

        menu = new JMenu("Inicio");
        menubar.add(menu);
        item = new JMenuItem("Salir");
            item.addActionListener(e -> quit());
        menu.add(item);

        menu = new JMenu("Usuarios");
        menubar.add(menu);
        item = new JMenuItem("Plantilla");
            item.addActionListener(e -> showStaff());
        menu.add(item);
        item = new JMenuItem("Clientes");
            item.addActionListener(e -> showCustom());
        menu.add(item);

        menu = new JMenu("Promociones");
        menubar.add(menu);
        item = new JMenuItem("Editar");
            item.addActionListener(e -> editPromos());
        menu.add(item);
        item = new JMenuItem("Lista");
            item.addActionListener(e -> listPromos());
        menu.add(item);
        item = new JMenuItem("Promociones activas");
            item.addActionListener(e -> currentPromos());
        menu.add(item);

        menu = new JMenu("Info");
        menubar.add(menu);
        item = new JMenuItem("Estadísticas");
            item.addActionListener(e -> metrics());
        menu.add(item);

        menu = new JMenu("About");
        menubar.add(menu);
        item = new JMenuItem("About TUNED");
            item.addActionListener(e -> about());
        menu.add(item);
        item = new JMenuItem("Ayuda");
            item.addActionListener(e -> help());
        menu.add(item);
    }
    private void editPromos() 
    {
        JOptionPane.showMessageDialog(frame, "Clientes", "No clientes", 
                JOptionPane.INFORMATION_MESSAGE);
    }
    private void listPromos() 
    {
        JOptionPane.showMessageDialog(frame, "Clientes", "No clientes", 
                JOptionPane.INFORMATION_MESSAGE);
    }
    private void currentPromos() 
    {
        JOptionPane.showMessageDialog(frame, "Clientes", "No clientes", 
                JOptionPane.INFORMATION_MESSAGE);
    }
    private void metrics() 
    {
        JOptionPane.showMessageDialog(frame, "Clientes", "No clientes", 
                JOptionPane.INFORMATION_MESSAGE);
    }
    private void about() 
    {
        JOptionPane.showMessageDialog(frame, "Clientes", "No clientes", 
                JOptionPane.INFORMATION_MESSAGE);
    }
    private void help() 
    {
        JOptionPane.showMessageDialog(frame, "Clientes", "No clientes", 
                JOptionPane.INFORMATION_MESSAGE);
    }
}
