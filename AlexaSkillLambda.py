import json
import boto3

iot_data_client = boto3.client('iot-data', region_name='us-east-1')

THING_NAME = "RompeMuellesIoT"
AUTHORIZED_USER_ID = "amzn1.ask.account.AMARWCD26PHCD2A7P5ZIQ7WUQ3KPKMWU4OVEGGTSFLDKGRTC7AUFXDVNQGDYQF2MKJY4QHGTUA56WRJY7SBNECFFOQGK53AOKPB7JMHOCGHFGPDRU3QFMZ33ORVNDXNX26DPHYAZTCW475B3EKCQZ3JF2OMBF2463ELWSOR52N3NXXUEUHJFYYKMTNDENOTEFLNGAQJGKRC5YD2NU2GMTYAUKVAMQHUG6NWFOZQ5VJWQ"  # ← reemplaza por tu verdadero userId de Alexa

def lambda_handler(event, context):
    try:
        user_id = event['session']['user']['userId']
        if user_id != AUTHORIZED_USER_ID:
            return {
                'version': '1.0',
                'response': {
                    'outputSpeech': {
                        'type': 'PlainText',
                        'text': 'No estás autorizado para usar esta skill.'
                    },
                    'shouldEndSession': True
                }
            }

        req_type = event['request']['type']

        if req_type == 'LaunchRequest':
            return build_response('Hola, bienvenido a RompeMuelles Inteligente. ¿Qué deseas hacer?')

        elif req_type == 'IntentRequest':
            intent_name = event['request']['intent']['name']

            if intent_name == 'GetSpeedIntent':
                try:
                    response = iot_data_client.get_thing_shadow(thingName=THING_NAME)
                    payload = json.loads(response['payload'].read())
                    last_speed = payload["state"]["reported"].get("lastSpeedDetected", "desconocida")

                    return build_response(f'La última velocidad detectada es {last_speed} centímetros por segundo.')
                except Exception as e:
                    print(f"Error obteniendo shadow: {e}")
                    return build_response('No pude obtener la velocidad detectada.')

            elif intent_name == 'OpenGateIntent':
                update_shadow("open")
                return build_response('He activado el rompe muelles.')

            elif intent_name == 'CloseGateIntent':
                update_shadow("close")
                return build_response('He desactivado el rompe muelles.')

            elif intent_name == 'AMAZON.HelpIntent':
                return build_response('Puedes preguntarme cuál es la última velocidad detectada, o pedirme abrir o cerrar el rompe muelles.')

            elif intent_name in ['AMAZON.CancelIntent', 'AMAZON.StopIntent']:
                return {
                    'version': '1.0',
                    'response': {
                        'outputSpeech': {
                            'type': 'PlainText',
                            'text': 'Adiós.'
                        },
                        'shouldEndSession': True
                    }
                }

            else:
                return build_response('No entendí tu solicitud. Por favor, intenta de nuevo.')
        else:
            return build_response('No entendí tu solicitud. Por favor, intenta de nuevo.')

    except Exception as e:
        print(f"Error general: {e}")
        return build_response('Hubo un error al procesar la solicitud.')

def build_response(text):
    return {
        'version': '1.0',
        'response': {
            'outputSpeech': {
                'type': 'PlainText',
                'text': text
            },
            'reprompt': {
                'outputSpeech': {
                    'type': 'PlainText',
                    'text': '¿Deseas hacer otra consulta o acción?'
                }
            },
            'shouldEndSession': False
        }
    }

def update_shadow(state):
    payload = {
        "state": {
            "desired": {
                "gateState": state
            }
        }
    }
    iot_data_client.update_thing_shadow(
        thingName=THING_NAME,
        payload=json.dumps(payload)
    )
