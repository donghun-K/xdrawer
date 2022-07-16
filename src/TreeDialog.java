import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import javax.swing.*;
import javax.swing.event.TreeModelListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;

public class TreeDialog extends JDialog {

  static class FigureTreeModel implements TreeModel {

    DrawerView view;
    ArrayList<Figure> figures;
    DefaultMutableTreeNode root;

    FigureTreeModel(DrawerView view) {
      this.view = view;
      figures = view.getFigures();
      constructTree();
    }

    public void constructTree() {
      root = new DefaultMutableTreeNode("Figure");

      int length = DrawerView.figureTypes.length;

      ArrayList<String> names = new ArrayList<String>();
      DefaultMutableTreeNode[] nodes = new DefaultMutableTreeNode[length];

      for (int i = 0; i < length; i++) {
        String name = DrawerView.figureTypes[i];
        names.add(name);
        DefaultMutableTreeNode node = new DefaultMutableTreeNode(name);
        root.add(node);
        nodes[i] = node;
        root.add(node);
      }
      for (Figure ptr : figures) {
        String figureTypeName = ptr.getClass().getName();
        int index = names.indexOf(figureTypeName);
        nodes[index].add(new DefaultMutableTreeNode(ptr));
      }
    }

    public Object getRoot() {
      return root;
    }

    public Object getChild(Object parent, int index) {
      DefaultMutableTreeNode pNode = (DefaultMutableTreeNode) parent;
      return pNode.getChildAt(index);
    }

    public int getChildCount(Object parent) {
      DefaultMutableTreeNode pNode = (DefaultMutableTreeNode) parent;
      return pNode.getChildCount();
    }

    public boolean isLeaf(Object node) {
      DefaultMutableTreeNode pNode = (DefaultMutableTreeNode) node;
      return pNode.isLeaf();
    }

    public int getIndexOfChild(Object parent, Object child) {
      DefaultMutableTreeNode pNode = (DefaultMutableTreeNode) parent;
      DefaultMutableTreeNode cNode = (DefaultMutableTreeNode) child;
      return pNode.getIndex(cNode);
    }

    public void valueForPathChanged(TreePath path, Object newValue) {

    }

    public void addTreeModelListener(TreeModelListener l) {

    }

    public void removeTreeModelListener(TreeModelListener l) {

    }
  }

  static class FigureTree extends JTree {

    FigureTreeModel model;

    FigureTree(DrawerView view) {
      super();
      model = new FigureTreeModel(view);
      setModel(model);
    }

    public void updateUI() {
      if (model != null) {
        model.constructTree();
        super.updateUI();
        setExpandedState(getPathForRow(0), true);
      }
    }
  }

  static class DialogPanel extends JPanel implements ActionListener {

    JDialog dialog;
    DrawerView view;
    JButton done;
    JButton remove;
    FigureTree tree;

    DialogPanel(JDialog dialog, DrawerView view) {
      this.view = view;
      this.dialog = dialog;
      setLayout(new BorderLayout());

      tree = new FigureTree(view);
      JScrollPane sp = new JScrollPane(tree);
      add(sp, BorderLayout.CENTER);

      JPanel bottom = new JPanel();
      bottom.add(remove = new JButton("Remove"));
      bottom.add(done = new JButton("Done"));
      add(bottom, BorderLayout.SOUTH);

      remove.addActionListener(this);
      done.addActionListener(this);
    }

    public void actionPerformed(ActionEvent e) {
      if (e.getSource() == remove) {
        TreePath selectedPath = tree.getSelectionPath();
        if (selectedPath == null) {
          return;
        }
        DefaultMutableTreeNode selectedNode = (DefaultMutableTreeNode) selectedPath.getLastPathComponent();
        updateUI();
        Object selectedObject = selectedNode.getUserObject();
        if (selectedObject instanceof Figure) {
          view.remove((Figure) selectedObject);
          updateUI();
        }
      } else if (e.getSource() == done) {
        dialog.setVisible(false);
      }
    }

    public void updateUI() {
      if (tree != null) {
        tree.updateUI();
      }
    }
  }

  TreeDialog(String title, DrawerView view) {
    super((JFrame) null, title);
    setLocation(200, 300);
    setSize(400, 300);

    Container container = getContentPane();
    JPanel panel = new TreeDialog.DialogPanel(this, view);
    container.add(panel);

    addWindowListener(new WindowAdapter() {
      public void windowActivated(WindowEvent e) {
        panel.updateUI();
      }
    });
  }
}
