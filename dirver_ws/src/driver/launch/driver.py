import rclpy
from motor_controller import MotorControllerNode
import yaml

def main(args=None):
    rclpy.init(args=args)

    # Charger les paramètres de configuration depuis le fichier YAML
    with open("motor_controller_config.yaml", "r") as config_file:
        config = yaml.safe_load(config_file)

    # Créer une instance du nœud MotorControllerNode avec les paramètres de configuration
    node = MotorControllerNode(cmd_vel_topic=config["motor_controller"]["cmd_vel_topic"],
                               motor_output_topic=config["motor_controller"]["motor_output_topic"])

    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__mainMotorControllerNode__':
    mainMotorControllerNode()
