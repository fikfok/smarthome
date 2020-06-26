from rest_framework import serializers

from metrics.models import Metrics


class MetricsSerializer(serializers.ModelSerializer):
    class Meta:
        model = Metrics
        fields = ('temperature', 'carbon_dioxide',)

